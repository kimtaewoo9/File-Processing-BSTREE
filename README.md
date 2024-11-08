# File Processing Report Tester (ver 2024)

This repository contains scripts to test the KMU File Processing report.

</br>

<img align="right" src="./assets/result.png" width="50%"/>

<div>
	<strong>Source must written in </strong>
	<code>C/C++ language</code> 
	<strong>and the file name must be </strong>
	<code>main.c</code> 
	<strong>or </strong>
	<code>main.cpp</code>
	<br>
	<br>
	<p>The script will do following tests:</p>
	<ul>
		<li>Check if the source file exists</li>
		<li>Check compilation of the source file</li>
		<li>Test the output of the program</li>
	</ul>
	<p>At the end of the test, a <code>deepthought</code>file will be generated, inside which you can find all the result and error/failure messages.</p>
</div>

</br>
</br>
</br>
</br>
</br>
</br>
</br>
</br>
</br>
</br>

# Supported Platforms

If you are not using GitHub Actions, please refer to the following platform requirements.

</br>

## Operating System

MacOS-sequoia15.0

</br>

## Compiler

Apple clang version 16.0.0 (clang-1600.0.26.3)

Target: arm64-apple-darwin24.1.0

Thread model: posix

InstalledDir: /Library/Developer/CommandLineTools/usr/bin

</br>

## Software Development Kit (SDK)

This tester is developed with `Non-standard SDK` below. It may not work on other SDKs.

```
$ ls /Library/Developer/CommandLineTools/SDKs

MacOSX.sdk MacOSX14.5.sdk MacOSX14.sdk MacOSX15.0.sdk MacOSX15.sdk
```

</br>
</br>
</br>
</br>

# Getting Started

## Installation

### Local machine

If you want to test on your `local machine`, `clone` this repository. It may require the same `platform` as above.

```

https://github.com/KMU-File-Processing/File-Processing-Report-Tester.git

```

</br>

### Github Actions (Recommended)

You can test your project on `Github Actions`. `fork` this repository and `enable` the Github Actions in the `Actions` tab in your repository.

❗️❗️❗️Must fork it as `Private` repository❗️❗️❗️

</br>

Or you can create a new repository with the `template` below.

```
https://github.com/KMU-File-Processing/File-Processing-Report-Tester/generate
```

❗️❗️❗️Must create it as `Private` repository either❗️❗️❗️

</br>

## Configuration

If you run the script for the first time, it will automatically create `my_config.sh` file and ask you to edit it with the path of your project.

</br>

## Testcase

You can add your own test cases in the [testcase](testcase) directory. The script will run all the test cases in the directory.

</br>
</br>
</br>
</br>

# Running tests

## Local Machine

Go to the directory where you cloned and run the script

```

bash grademe.sh

```

or run with the absolute path

```

bash /path/where/you/cloned/grademe.sh

```

</br>

## Github Actions

Place your source code in the `submit` directory.

</br>

### Test automatically

When you `push` your source code to the repository, Github Actions will automatically test your project.
Default project to test is `__bstree`. You can change the default project in the [main.yml](.github/workflows/main.yml) file.

</br>

### Test manually

You can manually run the workflow with `command` below or use the `Actions` tab in your repository.

```

gh workflow run main.yml -f project="your_project_name"

```

<img src="./assets/Github Actions.png" width="100%"/>

</br>

### Result

You can check the result of the test in the `Actions` tab in your repository.
`Deepthought` file will be generated in the `artifacts` section.

</br>
</br>
</br>
</br>

# License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

</br>
</br>
</br>
</br>

# Contact

If you have any questions, feel free to contact me at <mailto:younganswer@kookmin.ac.kr>

Any contributions are welcome! 🎉
