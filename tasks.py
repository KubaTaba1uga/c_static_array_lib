###############################################
#                Imports                      #
###############################################
import fnmatch
import logging
import os
import shutil
import sys
import traceback

from invoke import task

###############################################
#                Setup                        #
###############################################
# Configure logging
logging.basicConfig(
    level=logging.INFO, format="%(asctime)s - %(levelname)s - %(message)s"
)

# Define constants
BUILD_DIR = "build"

###############################################
#                Tasks                        #
###############################################

os.makedirs(BUILD_DIR, exist_ok=True)


@task
def setup(c, builddir=BUILD_DIR):
    """
    Set up the Meson build system.
    """
    logging.info("Setting up build directory: %s", builddir)
    command = ["meson", "setup", builddir]
    run_command(c, command)


@task
def build(c, builddir=BUILD_DIR):
    """
    Compile the project using the Meson build system.
    """
    logging.info("Compiling project in directory: %s", builddir)
    command = ["meson", "compile", "-C", builddir]
    run_command(c, command)


@task
def test(c, builddir=BUILD_DIR, test_name=None):
    """
    Run tests using the Meson build system.
    """
    logging.info("Reconfiguring build directory for tests: %s", builddir)
    configure_command = ["meson", "configure", builddir, "-Dtests=true"]
    run_command(c, configure_command)

    logging.info("Running tests in directory: %s", builddir)
    command = ["meson", "test", "-C", builddir]
    if test_name:
        command.append(test_name)
    run_command(c, command)


@task
def clean(c, builddir=BUILD_DIR):
    """
    Clean the build directory and Emacs temporary files.
    """
    EMACS_TEMP_FILES = ["*~", "*.swp", ".#*", ".emacs-places", ".emacs.desktop"]

    logging.info("Cleaning build directory: %s", builddir)
    if os.path.exists(builddir):
        shutil.rmtree(builddir)
        logging.info("Removed build directory: %s", builddir)
    else:
        logging.warning("Build directory does not exist: %s", builddir)

    logging.info("Cleaning Emacs temporary files...")
    for pattern in EMACS_TEMP_FILES:
        for file in glob_files(pattern):
            try:
                os.remove(file)
                logging.info("Removed file: %s", file)
            except Exception as e:
                logging.error("Failed to remove file: %s. Error: %s", file, e)


@task
def install(c):
    """
    Install all required dependencies for the project.
    """
    install_meson(c)
    install_ruby(c)


@task
def install_meson(c):
    """
    Install Meson build system if not already installed.
    """
    logging.info("Checking and installing Meson.")
    os_check = os.popen("hostnamectl | grep 'Operating System'").read()

    if command_exists("meson"):
        logging.info("Meson is already installed.")
        return

    if "Debian GNU/Linux" in os_check or "Ubuntu" in os_check:
        commands = [
            "sudo apt-get update",
            "sudo apt-get install -y python3-pip ninja-build",
            "sudo pip3 install meson",
        ]
    else:
        logging.error("Unsupported operating system for Meson installation.")
        sys.exit(1)

    for command in commands:
        run_command(c, command.split())


@task
def install_ruby(c):
    """
    Install Ruby if not already installed.
    """
    logging.info("Checking and installing Ruby.")
    os_check = os.popen("hostnamectl | grep 'Operating System'").read()

    if command_exists("ruby"):
        logging.info("Ruby is already installed.")
        return

    if "Debian GNU/Linux" in os_check:
        commands = [
            "sudo apt update",
            "sudo apt install -y ruby-full",
        ]
    else:
        logging.error("Unsupported operating system for Ruby installation.")
        sys.exit(1)

    for command in commands:
        run_command(c, command.split())


###############################################
#                Helpers                      #
###############################################


def run_command(process, command_l):
    """
    Execute a shell command using the given process and handle errors.
    """
    command = " ".join(command_l)
    logging.debug("Executing `%s`.", command)

    if not command_exists(command_l[0]):
        logging.error("Command not found: `%s`.", command_l[0])
        sys.exit(1)

    try:
        process.run(command, pty=True)
    except Exception as e:
        logging.error(
            "Command failed: `%s`. Error: %s", command, traceback.format_exc()
        )
        sys.exit(2)


def command_exists(command):
    """
    Check if a command exists on the system.
    """
    return shutil.which(command) is not None


def glob_files(pattern):
    """
    Find all files matching a given pattern in the current directory and subdirectories.
    """
    for root, dirs, files in os.walk("."):
        for file in files:
            if fnmatch.fnmatch(file, pattern):
                yield os.path.join(root, file)
