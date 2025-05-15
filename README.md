# DermaBase 🏥💻

DermaBase is a powerful yet easy-to-use application designed for dermatologists and their assistants to manage patient records efficiently. The suite includes two versions:

- DermaBase (Doctor)    >> For dermatologists to diagnose, prescribe, and manage patient history.
- DermaBase (Assistant) >> For assistants to handle patient intake, and medical documentation.


## Technology Stack

- Frontend: Qt (QtQuick/QML)
- Backend: Qt, C++
- Database: MySQL
- Build system: CMake


## Installation & Setup

For the easiest setup, download one of the prebuilt executables or installation packages from the Releases section. Download the latest version for your operating system (Windows, macOS, or Linux) and follow the installation instructions provided in the release notes.


## Project Setup

Before using this project and building it, ensure your development environment meets the following requirements for each OS:

### Windows

1. Install a MySQL service (preferably MySQL Workbench) and use the provided SQL files to setup the database.
2. Install and open the [Qt Online Installer](https://www.qt.io/download-qt-installer-oss) for Windows.
3. Install Qt Framework (Version 6.8 LTS) & QtCreator using the installer.
4. Clone the repository and open the CMakeLists.txt file in the Qt Creator.
5. Configure the project with your favourite compiler (preferably MSVC).
6. Build the project.
7. Place the provided drivers for MySQL into the build folder.
8. Run the project.

### macOS

1. Install a MySQL service (preferably MySQL Workbench) and use the provided SQL files to setup the database.
2. Install and open the [Qt Online Installer](https://www.qt.io/download-qt-installer-oss) for macOS.
3. Install Qt Framework (Version 6.8 LTS) & QtCreator using the installer.
4. Clone the repository and open the CMakeLists.txt file in the Qt Creator.
5. Configure the project with your favourite compiler.
6. Build the project.
7. Place the provided drivers for MySQL into the build folder.
8. Run the project.

### Linux

1. Install a MySQL service (preferably MySQL Workbench) and use the provided SQL files to setup the database.
2. The project uses a MySQL database. Therefore, you may need to install additional packages to make the project work on Linux:
```diff
sudo apt install libmysqlclient-dev
```
3. Since QML uses OpenGL, on Linux systems, you may need to install additional dependencies to avoid errors:
```diff
sudo apt install libglx-dev libgl1-mesa-dev
```
4. The project uses the 'PrintSupport' module. Therefore, you may need to install the CUPS printing system module for Linux:
```diff
sudo apt-get install libcups2-dev
```
5. Install and open the [Qt Online Installer](https://www.qt.io/download-qt-installer-oss) for Linux.
6. Install Qt Framework (Version 6.8 LTS) & QtCreator using the installer.
7. Clone the repository and open the CMakeLists.txt file in the Qt Creator.
8. Configure the project with your favourite compiler.
9. Build the project.
10. Place the provided drivers for MySQL into the build folder.
11. Run the project.


## Drivers

Whether you are trying to run the application or simply set up the project on your device, you will need drivers for the MySQL database. For legal reasons, Qt cannot ship these drivers directly. Therefore, you must obtain them manually from the following link:

[MySQL drivers](https://github.com/thecodemonkey86/qt_mysql_driver)

Choosing the correct driver can mean the difference between a fully functional and a horrible experience. Please make sure that the version that you select for your system has support for transactions as well. When you download the zip, simply place all the contents directly in the same location next to the executable.

For convienice we also provide the drivers directly in the project.


## Documentation

The following are useful links for this project:

- [Executing SQL Statements](https://doc.qt.io/qt-6.7/sql-sqlstatements.html)
- [internationalization (layout)](https://doc.qt.io/qt-6/qtquick-positioning-righttoleft.html)
- [Python Official Docs](https://docs.python.org/3/)
- [Threads in Qt](https://www.youtube.com/watch?v=dcSsjxhazu0)
- [Signals and Slots in Qt](https://www.youtube.com/watch?v=QvV3WMFCQMU)

## Backup

There are 2 ways to approach backups:

1. You can watch this video on how to do it directly in Workbench: https://www.youtube.com/watch?v=DaAbmHJUmKM
2. You can create a script to do it automatically for you using mysqldump program. (We have some premade scripts available in the project)

## Notification system (In progress)

We plan on cretaing an SMTP module or a SMS module to enable sending notifications to patients.

## Installing MySQL Workbench:

Here is a very good video for installing MySQL workbench: https://www.youtube.com/watch?v=Yw3NNvqk-2o

## Contributing

We welcome contributions! Feel free to submit issues, feature requests, or pull requests. We always welcome sponsorships and sincerely appreciate any financial contributions to the project. Your support is what helps keep it free and accessible to everyone.
