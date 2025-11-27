#include "what.h"

int what_message(const char number[], const char message[])
{
    char encodedMessage[256];
    char encodedNumber[64];
    char url[512];
    char command[700];

    if (encode_url(encodedMessage, sizeof(encodedMessage), message) != 0)
    {
        printf("Failed to encode message buffer too small.\n");
    }

    if (encode_url(encodedNumber, sizeof(encodedNumber), number) != 0)
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
