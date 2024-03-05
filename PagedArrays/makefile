all : Array.class ArrayManager.class ArrayClient.class SegmentationViolationException.class OutOfMemoryException.class

clean :
	-rm *.class 2> /dev/null

Array.class : Array.java
	javac Array.java

ArrayManager.class : ArrayManager.java
	javac ArrayManager.java

ArrayClient.class : ArrayClient.java
	javac ArrayClient.java

SegmentationViolationException.class : SegmentationViolationException.java
	javac SegmentationViolationException.java

OutOfMemoryException.class : OutOfMemoryException.java
	javac OutOfMemoryException.java

run :
	@clear
	@echo "Test #1"
	@java ArrayClient < arr1.txt
	@echo
	@echo "Test #2"
	@java ArrayClient < arr2.txt
	@echo
	@echo "Test #3"
	@java ArrayClient < arr3.txt
	@echo
	@echo "Test #4"
	@java ArrayClient < arr4.txt
	@echo
	@echo "Test #5"
	@java ArrayClient < arr5.txt
	@echo
	@echo "Test #6"
	@java ArrayClient < arr6.txt
	@echo
	@echo "Test #7"
	@java ArrayClient < arr7.txt
	@echo
	@echo "Test #8 - Extra Credit: COW (Copy on Write)"
	@java ArrayClient < arr8.txt
