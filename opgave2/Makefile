help:
	@echo "HELP!"
	@echo "targets:"
	@echo "	build-opgave2"
	@echo "	run-opgave2"

build-opgave2:
	gcc redirect.c forback.c opgave2test.c -o opgave2

run-opgave2: build-opgave2
	./opgave2
	#Because of problems with rights after refactoring
	#we have to explicitly set read access
	chmod u+rw test.txt
	cat test.txt

clean:
	rm test.txt opgave2
