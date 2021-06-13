#! /usr/bin/sh

# cria o arquivo README.new na raiz
/usr/bin/env python3 update_readme.py ../../README.md ../.. -o ../../README.new &&
/usr/bin/mv ../../README.new ../../README.md
