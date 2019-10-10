all:
	mkdir -p target
	meson target
	cd target && ninja
	cd target ./cnake

