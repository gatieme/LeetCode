int charTointValue(char c)
{
    int data = 0;

    switch (c) {
        case 'I':
            data = 1;
            break;
        case 'V':
            data = 5;
            break;
        case 'X':
            data = 10;
            break;
        case 'L':
            data = 50;
            break;
        case 'C':
            data = 100;
            break;
        case 'D':
            data = 500;
            break;
        case 'M':
            data = 1000;
            break;
    }

    return data;
}


int romanToInt(char* s)
{
    if(!s)
        return 0;
    int len = strlen(s);
    int i = 0;
    int sum = 0;
    int pre = 0;
    int cur = 0;
    sum = charTointValue(s[0]);

    for(i = 1;i < len;i ++) {
        pre = charTointValue(s[i-1]);
        cur = charTointValue(s[i]);
        if(cur <= pre) {
            sum = sum + cur;
        }
        else {
            sum = sum - 2*pre + cur;
        }
    }
    return sum;
}

