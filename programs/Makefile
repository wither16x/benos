MAKEFLAGS += --no-print-directory

all:
	@for dir in * ; do \
		[ -d "$$dir" ] || continue ; \
		echo "Building $$dir..." ; \
		$(MAKE) -C "$$dir" ; \
	done

clean:
	@for dir in * ; do \
		[ -d "$$dir" ] || continue ; \
		echo "Cleaning $$dir..." ; \
		$(MAKE) -C "$$dir" clean ; \
	done

.PHONY: all clean