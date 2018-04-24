CFLAGS := \
	-Wall -std=c11 \
	-I. -MMD

OBJS := \
	avl.o \
	ht.o \
	list.o \
	rb.o

deps := $(OBJS:%.o=%.d)

TESTS := \
	tests/avl \
	tests/ht \
	tests/list \
	tests/rb

tests/%: tests/%.o
	$(CC) $(CFLAGS) -o $@ $^ $(OBJS)
deps += $(TESTS:%=%.d)

all: $(OBJS)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    PRINTF = printf
else
    PRINTF = env printf
endif

PASS_COLOR = \e[32;01m
NO_COLOR = \e[0m
tests/%.done: tests/%
	@$(PRINTF) "*** Validating $< ***\n"
	@./$< && $(PRINTF) "\t$(PASS_COLOR)[ Verified ]$(NO_COLOR)\n"
check: $(OBJS) $(addsuffix .done, $(TESTS))

clean:
	$(RM) $(deps) $(OBJS) $(TESTS) $(TESTS:%=%.o)

-include $(deps)
