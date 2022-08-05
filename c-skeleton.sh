#!/bin/bash

# I don't want to know how many hours were stolen from my life since a year back by creating
# all my (mostly minor experiments) C-projects manually. In order to solve this, I finally
# begun to play around with my very first Bash-script.

cat << INTRO
C-SKELETON==================================================================================

Written by Jakob Fredriksson, stateloader@protonmail.com

Script that creates a simple C-skeleton. Just enter your name and the name of the project.
It's ok to skip your own name. The project itself, however, must be named. Max 16 characters
long without any whitespaces.

If something forbidden is detected during input the script will terminate, hopefully with an
explanation. I have no idea how the script will respond if MAKEFILE isn't in place on your
OS, even less if it isn't a Linux dist.

============================================================================================

INTRO

DATE=$( date )

#	User being prompted for her/his name (creator of the project) and a name of the project.
# It's OK to yolo and just press enter to CREATOR but PROJECT must be assigned.

read -p 'Enter your name(s): ' CREATOR
if [ ${#CREATOR} -lt 1 ]; then
	CREATOR=$USER
elif [ ${#CREATOR} -gt 31 ]; then
	echo "My word you've a long and pretty name! Too long, actually. Run the script again but"
  echo "keep it under 33 characters. Terminating."
	exit 1
fi

read -p 'Enter project name: ' PROJECT
if [ ${#PROJECT} -lt 1 ]; then
	echo "You haven't given the project a name. Run the script again! Terminating."
  exit 1
elif [[ $PROJECT == *" "* ]]; then
	echo "A project-name can't contain spaces. Run the script again! Terminating."
  exit 1
elif [ ${#PROJECT} -gt 15 ]; then
	echo "Name too long. Run the script again and keep it under 17 charachters. Terminating."
  exit 1
elif [ -d "$PROJECT-project" ]; then
	echo "\"$PROJECT\" already exist. Change dir or pick another project-name. Terminating."
	exit 1
fi

# Upcoming functions create and append files with some base-content. The content is
# collected into a string-array and appended item by item whithin a for-loop for each file.

create_readme() {
#	Creates a README containing some default data.

  touch README.md

	local -a content=(
		"ABOUT" "	Project \"$PROJECT\"" "GENERAL" "	created by $CREATOR, $DATE"
  )
  for i in "${content[@]}"; do
		echo "$i" >> README.md
  done
}

create_makefile() {
# Creates a make containing some basic commands.

	touch Makefile

	local -a content=(
		"make:" "	gcc -o ${PROJECT,,} source/*c -Wall -Wextra -g" "clean:" "	rm -f ${PROJECT,,}"
	)
	for i in "${content[@]}"; do
		echo "$i" >> Makefile
  done
}

create_main() {
# Creates a main containing standard includes and the mainfunction.

  touch main.c

  local -a content=(
		"#include <stdio.h>" "#include <stdlib.h>" "#include \"${PROJECT,,}.h\"" ""
		"int main(void) {" "" " printf(\"Hello $PROJECT\n\");" " return 0;" "" "}"
	)
  for i in "${content[@]}"; do
    echo "$i" >> main.c
  done
}

create_header() {
# Creates a project header-file containing includes for std variable types.

	touch ${PROJECT,,}.h

	local -a content=(
		"#ifndef ${PROJECT^^}_H_" "#define ${PROJECT^^}_H_" "" "#include <stddef.h>"
		"#include <stdint.h>" "" "#endif"
  )
  for i in "${content[@]}"; do
  	echo "$i" >> ${PROJECT,,}.h
  done
}

create_source() {
# Creates a project source-file containing standard includes.

  touch ${PROJECT,,}.c

  local -a content=(
		"#include <stdio.h>" "#include <stdlib.h>" "#include \"${PROJECT,,}.h\""
	)
	for i in "${content[@]}"; do
		echo "$i" >> ${PROJECT,,}.c
  done
}

create_project() {
#	Sewing everything together.

	mkdir $PROJECT"_project"; cd $PROJECT"_project"

	create_readme
	create_makefile

  mkdir slask source; cd source

  create_main
	create_header
	create_source

	if [ $? -gt 0 ]; then
		echo "Something went horrible wrong during setup. Bye!"
  	exit $?
	fi
}

create_project

cat << OUTRO

Project "$PROJECT" has successfully been created!

Go ahead and visit the project folder and type "make". Run binary ${PROJECT,,}.
If nothing went wrong the program should print "Hello $PROJECT" to your screen.

Happy coding!

==================================================================================C-SKELETON
OUTRO

exit $?
