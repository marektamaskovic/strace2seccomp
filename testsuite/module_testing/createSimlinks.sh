#!/bin/bash

ls -A ../../src | grep -e "[ch]pp" | grep -v "main" | grep -v "source.cpp" | xargs -p -I {} ln -s ../../src/{} {}
