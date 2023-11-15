for (int i = 0; i < strlen(InputSex); i++) {
                if (InputSex[i] != 10 || InputSex[i] != -10 || InputSex[i] != 127) { TempInputSex[i] = toupper((unsigned char)InputSex[i]);
                } else break;
            }