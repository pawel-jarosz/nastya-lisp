
![Build and run tests](https://github.com/pawel-jarosz/nastya-lisp/workflows/Build%20and%20run%20tests/badge.svg?branch=devel?event=push)

![Motto](https://media1.tenor.com/images/fef6738d7beb047b31dc357ce23b8d72/tenor.gif?itemid=18358101 "What I think about language with female name after playaround with Julia language :)")

# Nastya Lisp

## About project

It is an implementation of simple Lisp-like language written in C++17 written for educational reason to playaround with clean code architecture, compiler design and C++17.

**Lisp** is an abbreviation from **LIS**t **P**rocessing because the basic data structure are lists. Even function calls has following structure:

```lisp
(command_name list_of_arguments)
```

**Why Nastya Lisp**

I didn't have an idea for the language name but during implementing typesystem I've heard nice, women voice from YouTube movie that calls *Privet eto Nastya!*.

## Content

Repository contains the following content:

* *src* - directory with source code
* *build* - official build directory, used by docker scripts
* *docker* - docker image description
* *scripts* - utility scripts used during development for applying formatting or building software in docker

## Testing environment

Software was tested on the following environments:


| Name | Operating System | CPU |  Compilers |
|------|------------------|-----------|------|
| Private machine   | Manjaro 20.2 Nibia | Intel i5-5200U | gcc-10.2.0, clang-11.0.0|
| Github CI | ubuntu:latest | ? | gcc-10, clang-10 |
|

## Building process

### Build in docker
If you prefer to build application inside docker it is rather easy task :) Only you have to do to execute in terminal

```bash
> cd scripts
> ./build_docker.sh # to build docker image
> ./build_in_docker.sh # for building application
```

### Manual build

Before you try to build application your build machine should fullfilled some basic expectations:

* **Google Test**, i.e. from [here](https://github.com/google/googletest)

* **But library**, i.e. from [here](https://github.com/el-bart/but)
* **Nlohmann JSON** - it is dependency required by **But**, sources are available  [here](https://github.com/nlohmann/json.git)
* installed **boost** libraries
* installed compiler with support for C++17 standard and cmake

When your machine fullfills this requirenments you have to follow instruction:

```bash
> cd build
> cmake ..
> make
> make test # optional, for running tests
```

To run command-line interpreter you have to execute it in project directory:

```bash
cd build/bin
./nastya-cli
```

After that you should see command prompt:

``` bash
? |
```


## Examples

At this moment functionalities are very limited and supports only following functions:

    Head - it returns first element of the list
    Tail - returns list except the first element
    Quote - returns list without evaluating values inside
    Exit-Console - terminal shutdown

There is implemented syntactic sugar for ***Quote*** command - it is single quote character!

**Warning** - comments are not implemented, just omit it during typing.

```lisp
? | #true
  | Boolean => #true // similarily #false
? | "abc"
  | String => abc
? | (Quote (1 "abc" 2.3))
  | List => (1 "abc" 2.3) // lists are heterogenous structure
? | '(1 "abc" 2.3)        // usage of syntactic sugar for quote
  | List => (1 "abc" 2.3)
? | (Head '(1 2 3))
  | Integer => 1
? | (Tail '(1 2 3))
  | List => (2 3)
? | (Head (Tail (Quote ("abc" (2 #true 3.4) 3))))
  | List => (2 $true 3.4)
```
