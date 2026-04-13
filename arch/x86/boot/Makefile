ASFLAGS := --32

boot.o: boot.S
	as $(ASFLAGS) $< -o $@

clean:
	rm -f *.o

.PHONY: clean
