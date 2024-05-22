<h1 align="center">C Language Preprocessor</h1>

<p align="justify"> This is a simple C/C++ preprocessor. The goal is to have good conformance with the C and C++ standards and to handle nonstandard preprocessor extensions in gcc / clang / visual studio preprocessors. Most of the preprocessor testcases in gcc and clang are handled OK by so-cpp.
    <br> 
</p>

## 📝 Table of Contents
- [About](#about)
- [Getting Started](#getting_started)
- [Usage](#usage)
- [Built Using](#built_using)
- [Authors](#authors)

## 🧐 About <a name = "about"></a>
The C Preprocessor is not a part of the compiler, but is a separate step in the compilation process. In simple terms, a C Preprocessor is just a text substitution tool and it instructs the compiler to do required pre-processing before the actual compilation.


<img src="./res/Preprocessor-In-C.png">


## 🏁 Getting Started <a name = "getting_started"></a>
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See [deployment](#deployment) for notes on how to deploy the project on a live system.

### Prerequisites
To run the preprocessor on your computer you must have:
* for **UNIX** based operating systems: 
    * **gcc** - is a tool from the [GNU Compiler Collection](https://linuxize.com/post/how-to-install-gcc-compiler-on-ubuntu-18-04/) used to compile and link C programs
* for **Windows** operating system: 
    * **cl** -  is a tool that controls the [Microsoft C++](https://docs.microsoft.com/en-us/cpp/build/reference/compiler-options?view=vs-2019) compiler and linker

### Installing
This is a step by step series of examples that tell you how to get a development env running.

* **Linux**:
    * start by updating the packages list
        ```shell-script
        $ sudo apt update
        ```
    * install the build-essential package(a package of new packages including gcc, g++ and make) by typing:
        ```shell-script
        $ sudo apt install build-essential 
        ```
* **Windows**:
    * all you need to do to install **cl** on your machine is to install the [*Microsoft Visual Studio Comunity Edition*](https://visualstudio.microsoft.com/).

## 🔧 Running the tests <a name = "tests"></a>
If you want to run the automated tests for Linux system you must follow the following steps:
* clone the repository by copping the following command in your terminal:
    ```bash
    git clone https://github.com/gabriel-rusu/C-Language-Preprocessor.git
    ```
* go into the project director and run the following command:
    ```bash
    $ make test
    ```
* now in the test director a new folder **_test/outputs** has appeared containing the results.

The purpose of the test suite is to show the preprocessing of .c and .h files from the **_test/inputs** folder. The results of the preprocessed files is then compared with the CPP output (utilitary of GCC that is used to preprocess the .c and .h files for the GCC compiler) 

## 🎈 Usage <a name="usage"></a>
To use the preprocessor on other files, simply use the following command:
```bash
    ./so-cpp < your-input-file.in >your-output-file.out
```
where:
* your-input-file.in - is a custom input file
* your-output-file.out - is the result of pteprocessing the input file


## ⛏️ Built Using <a name = "built_using"></a>
- [Visual Studio Code](https://code.visualstudio.com/) - code editor
- [GCC](https://gcc.gnu.org/) - used to compile the program on my Linux machine
- [CPP](https://www.codeproject.com/Articles/3853/Wave-a-Standard-conformant-C-preprocessor-library) - preprocessing utility used to test the program output

## ✍️ Author <a name = "authors"></a>
- [@gabriel-rusu](https://github.com/gabriel-rusu) - Idea & Initial work
