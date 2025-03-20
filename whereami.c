/**
 * whereami.c - A program to display system information and SSH connection details
 * 
 * Compile with: gcc -o whereami whereami.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <time.h>
#include <sys/types.h>

#define COLOR_RESET   "\x1B[0m"
#define COLOR_BLUE    "\x1B[34m"
#define COLOR_GREEN   "\x1B[32m"
#define COLOR_YELLOW  "\x1B[33m"
#define COLOR_RED     "\x1B[31m"
#define COLOR_MAGENTA "\x1B[35m"
#define COLOR_CYAN    "\x1B[36m"

void print_header(const char *title) {
    printf("\n%s=== %s ===%s\n", COLOR_CYAN, title, COLOR_RESET);
}

int main() {
    // Get hostname
    char hostname[HOST_NAME_MAX + 1];
    if (gethostname(hostname, HOST_NAME_MAX + 1) != 0) {
        strcpy(hostname, "Unknown");
    }
    
    // Get username
    struct passwd *pw = getpwuid(getuid());
    const char *username = pw ? pw->pw_name : "Unknown";
    
    // Get system information
    struct utsname system_info;
    if (uname(&system_info) != 0) {
        fprintf(stderr, "Failed to get system information\n");
        return EXIT_FAILURE;
    }
    
    // Get current time
    time_t current_time = time(NULL);
    char time_str[100];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&current_time));
    
    // Check if SSH connection
    char *ssh_client = getenv("SSH_CLIENT");
    char *ssh_connection = getenv("SSH_CONNECTION");
    char *ssh_tty = getenv("SSH_TTY");
    int is_ssh = (ssh_client != NULL || ssh_connection != NULL || ssh_tty != NULL);
    
    // Extract SSH client IP if available
    char ssh_source_ip[128] = "Unknown";
    if (ssh_connection != NULL) {
        sscanf(ssh_connection, "%s", ssh_source_ip);
    } else if (ssh_client != NULL) {
        sscanf(ssh_client, "%s", ssh_source_ip);
    }
    
    // Get current working directory
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        strcpy(cwd, "Unknown");
    }
    
    // Get terminal
    char *terminal = getenv("TERM");
    if (terminal == NULL) {
        terminal = "Unknown";
    }
    
    // Get shell
    char *shell = getenv("SHELL");
    if (shell == NULL) {
        shell = "Unknown";
    }
    
    // Display information
    printf("\n%s╭─────────── WHERE AM I? ───────────╮%s\n", COLOR_GREEN, COLOR_RESET);
    
    print_header("System Information");
    printf("%sHostname      :%s %s\n", COLOR_YELLOW, COLOR_RESET, hostname);
    printf("%sSystem        :%s %s %s\n", COLOR_YELLOW, COLOR_RESET, system_info.sysname, system_info.release);
    printf("%sKernel Version:%s %s\n", COLOR_YELLOW, COLOR_RESET, system_info.version);
    printf("%sArchitecture  :%s %s\n", COLOR_YELLOW, COLOR_RESET, system_info.machine);
    printf("%sDate & Time   :%s %s\n", COLOR_YELLOW, COLOR_RESET, time_str);
    
    print_header("User Information");
    printf("%sUser          :%s %s\n", COLOR_YELLOW, COLOR_RESET, username);
    printf("%sWorking Dir   :%s %s\n", COLOR_YELLOW, COLOR_RESET, cwd);
    printf("%sShell         :%s %s\n", COLOR_YELLOW, COLOR_RESET, shell);
    printf("%sTerminal      :%s %s\n", COLOR_YELLOW, COLOR_RESET, terminal);
    
    print_header("Connection Information");
    if (is_ssh) {
        printf("%sConnection    :%s %sRemote SSH%s\n", COLOR_YELLOW, COLOR_RESET, COLOR_RED, COLOR_RESET);
        printf("%sSSH Source    :%s %s\n", COLOR_YELLOW, COLOR_RESET, ssh_source_ip);
        if (ssh_tty != NULL) {
            printf("%sSSH TTY       :%s %s\n", COLOR_YELLOW, COLOR_RESET, ssh_tty);
        }
    } else {
        printf("%sConnection    :%s %sLocal Terminal%s\n", COLOR_YELLOW, COLOR_RESET, COLOR_BLUE, COLOR_RESET);
    }
    
    // Get environment variables that might be relevant
    char *display = getenv("DISPLAY");
    if (display != NULL) {
        printf("%sX Display     :%s %s\n", COLOR_YELLOW, COLOR_RESET, display);
    }
    
    char *session_type = getenv("XDG_SESSION_TYPE");
    if (session_type != NULL) {
        printf("%sSession Type  :%s %s\n", COLOR_YELLOW, COLOR_RESET, session_type);
    }
    
    printf("%s╰─────────────────────────────────╯%s\n\n", COLOR_GREEN, COLOR_RESET);
    
    return EXIT_SUCCESS;
}
