#! /usr/bin/sh

# cria o arquivo README.new na raiz
/usr/bin/env python3 update_readme.py ../../README.md ../.. -o ../../README.new &&
/usr/bin/diff ../../README.new ../../README.md

read -p "Continue (y/n)?" choice
case "$choice" in 
  y|Y ) /usr/bin/mv ../../README.new ../../README.md;;
  n|N ) /usr/bin/rm ../../README.new;;
  * ) echo "invalid"; /usr/bin/rm ../../README.new;;
esac
