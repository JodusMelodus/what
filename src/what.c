#include "what.h"

int __encode_url(char *dest, size_t dest_size, const char *src)
{
    size_t di = 0;

    for (size_t si = 0; src[si] != '\0'; si++)
    {
        unsigned char c = (unsigned char)src[si];

        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
        {
            if (di + 1 >= dest_size)
                return -1;
            dest[di++] = c;
        }
        else
        {
            if (di + 3 >= dest_size)
                return -1;
            snprintf(&dest[di], 4, "%%%02X", c);
            di += 3;
        }
    }

    if (di >= dest_size)
        return -1;
    dest[di] = '\0';
    return 0;
}

int what_message(const char number[], const char message[])
{
    char encodedMessage[256];
    char encodedNumber[64];
    char url[512];
    char command[700];

    if (__encode_url(encodedMessage, sizeof(encodedMessage), message) != 0)
    {
        printf("Failed to encode message buffer too small.\n");
    }

    if (__encode_url(encodedNumber, sizeof(encodedNumber), number) != 0)
    {
        printf("Failed to encode number buffer too small.\n");
    }

    snprintf(
        url,
        sizeof(url),
        "https://web.whatsapp.com/send/?phone=%s&text=%s&type=phone_number&app_absent=0",
        encodedNumber,
        encodedMessage);

#ifdef _WIN32
    ShellExecute(0, "open", url, 0, 0, SW_SHOWNORMAL);

    Sleep(5000);

    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wVk = VK_RETURN;
    ip.ki.wScan = 0;
    ip.ki.dwFlags = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    SendInput(1, &ip, sizeof(INPUT));

    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));

#elif __APPLE__
    snprintf(command, sizeof(command), "open %s");
    system(command);
#elif __linux__
    snprintf(command, sizeof(command), "xdg-open %s");
    system(command);
#else
    printf("What the hell are you using!?");
#endif

    return 0;
}
