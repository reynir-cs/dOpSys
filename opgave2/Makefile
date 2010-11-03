help:
	@echo "HELP!"
	@echo "targets:"
	@echo "	build-opgave2"
	@echo "	run-opgave2"

build-opgave2:
	gcc redirect.c forback.c opgave2test.c -o opgave2

run-opgave2: build-opgave2
	./opgave2
	# Going to cat test.txt
	cat test.txt

clean:
	rm test.txt opgave2
