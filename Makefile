bintree:bintree.c
	gcc -g $^ -o $@

.PHONY:clean
	clean:
		rm bintree
