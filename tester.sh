#!/usr/bin/env bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/29 18:59:18 by fmaurer           #+#    #+#              #
#    Updated: 2025/04/29 18:59:18 by fmaurer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# quick and dirty tester for invalid minirt scenefiles

TESTDIR=./rtfiles/testing/malformed-rtfiles
SOMETHINGWRONG=0

if [ ! -e ./minirt ]; then
	echo ">>> minirt not found!"
	exit 1
fi

if [ ! -e $TESTDIR ]; then
	echo ">>> test dir not found!"
	exit 1
fi

if [ "$(ls -1 $TESTDIR | wc -l)" -eq 0 ]; then
	echo ">>> testdir empty!"
	exit 1
fi

for i in $(ls -1 $TESTDIR); do
	if [ ! "$(echo $i | cut -f 1 -d '_')" = "TEMPLATE" ]; then
		echo -e "\e[38;5;106m>>> testing file \e[38;5;111m$TESTDIR/$i:\e[0m"
		echo -e "\e[38;5;106m---\e[0m"
		./minirt $TESTDIR/$i > /dev/null
		if [ $? -ne 1 ]; then
			SOMETHINGWRONG=1
		fi
		echo -e "\e[38;5;106m---\e[0m"
		echo -e "\e[38;5;106m>>> done testing file \e[38;5;111m$i.\e[0m"
		read -r
	fi
done

if [ $SOMETHINGWRONG -eq 0 ]; then
		echo -e "\e[38;5;106m>>> finy fine!\e[0m"
fi

