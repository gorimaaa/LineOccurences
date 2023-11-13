.PHONY: clean dist

dist: clean
	tar -hzcf "$(CURDIR).tar.gz" bst/* holdall/* lnid_test/* options/* makefile

clean:
	$(MAKE) -C lnid_test clean
