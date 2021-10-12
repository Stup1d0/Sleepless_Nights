#include <stdio.h>
#include <locale.h>

struct int1024_t{
    char num[1024];
    int error;
    int sign;
};
struct int1024_t from_int (int x){
    struct int1024_t tr;
    tr.sign = 1;
    if (x < 0){
        tr.sign = -1;
        x *= -1;
    }
    for(int i = 0; i < 1024; i++)
    {
        int dig = x % 10;
        tr.num[1023-i] = dig + '0';
        x /= 10;
    }
    tr.error = 0;
    return tr;
}                   //              перевод с инта в длинную переменную
struct int1024_t become_zero ( ){
    struct int1024_t result;
    result.sign = 1;
    result.error = 0;
    for (int i = 0; i < 1024; ++i) {
        result.num[i] = '0';
    }
    return result;
} // зануление, полезная функция на самом то деле
struct int1024_t unsigned_add_op (struct int1024_t x, struct int1024_t y){

    int add = 0;
    struct int1024_t ans;
    ans.error = 0;
    for (int i = 1023; i >= 0; --i)
    {
        int x_int = x.num[i]-'0';
        int y_int = y.num[i]-'0';
        int ans_int = x_int + y_int + add;
        add = ans_int / 10;
        ans.num[i] = ans_int % 10 + '0';
    }
    if(add == 1)
        ans.error = 1;
    return ans;
}// беззнаковое сложение, для реализации знаковых операций
int compare_op ( struct int1024_t x, struct int1024_t y){
    if(x.error == 1 || y.error == 1)
    {
        printf("%s", "Undefined Behavior of one of the Variables");
        return 404;
    }
    if(x.sign != y.sign)
    {
        if (x.sign == 1)
            return 1;
        if (y.sign == 1)
            return 2;
    }
    if (x.sign == 1)
        for (int i = 0; i < 1023; ++i)
        {
             if(x.num[i] < y.num[i])
            {
                return 2;
            }
            if(x.num[i] > y.num[i])
            {
                return 1;
            }
        }
    if (x.sign == -1)
        for (int i = 0; i < 1023; ++i)
        {
            if(x.num[i] < y.num[i])
            {
                return 1;
            }
            if(x.num[i] > y.num[i])
            {
                return 2;
            }
        }
    return 0;
}//сравнение чисел, 1 если больше первое, 2 если больше второй, 0 если они равны
int unsigned_compare_op ( struct int1024_t x, struct int1024_t y){

    for (int i = 0; i < 1023; ++i)
    {
        if(x.num[i] < y.num[i])
        {
            return 2;
        }
        if(x.num[i] > y.num[i])
        {
            return 1;
        }
    }
    return 0;
} //беззнаковое сравнение чисел
void swap (struct int1024_t x, struct  int1024_t y){

    for(int i = 0; i < 1024; ++i)
    {
        char num_bufer = x.num[i];
        x.num[i] = y.num[i];
        y.num[i] = num_bufer;
    }
    int sign_bufer = x.sign;
    x.sign = y.sign;
    y.sign = sign_bufer;
    int error_bufer = x.error;
    x.error = y.error;
    y.error = error_bufer;
}    //меняет местами значения числа x и у
struct int1024_t unsigned_subtr_op (struct int1024_t x, struct int1024_t y){
    struct int1024_t ans;
    if(unsigned_compare_op(x ,y) == 0)
    {
        for (int i = 0; i < 1023; ++i)
        {
            ans.num[i] = '0';
        }
        ans.error = 0;
        return ans;
    }
    int subtr = 0;
    ans.error = 0;
    for (int i = 1023; i >= 0; --i)
    {
        int x_int = x.num[i] - '0' - subtr;
        int
        y_int = y.num[i] - '0';
        if(x_int < y_int)
            subtr = 1;
        else
            subtr = 0;
        int ans_int = x_int - y_int + subtr * 10;
        ans.num[i] = ans_int + '0';
    }
    return ans;
} // беззнаковое вычетание, для реализации знаковых операций
void printf_value (struct int1024_t x) {
    if(x.error == 1)
    {
        printf("%s", "Undefined Behavior");
        return;
    }
    int last_dig_pointer = 1024;
    for (int i = 0; ; ++i)
    {
        if (x.num[i] != '0')
        {
            last_dig_pointer = i;
            break;
        }
    }
    if ( x.sign == -1){
        printf("%c", '-');
    }
    if(last_dig_pointer == 1024)
    {
        printf("%c", '0');
        return;
    }

    for ( last_dig_pointer; last_dig_pointer != 1024; ++last_dig_pointer)
        printf("%c", x.num[last_dig_pointer]);


} // вывод
struct int1024_t add_op (struct int1024_t x, struct int1024_t y){
    struct int1024_t ans;
    if (x.sign == y.sign){
        ans = unsigned_add_op(x, y);
        ans.sign = x.sign;
        return ans;
    }
    if(x.sign != y.sign){
        int bigger_sum = unsigned_compare_op(x, y);
        if (bigger_sum == 0){
            ans = become_zero();
            return ans;
        }
        if(x.sign == -1 && bigger_sum == 1){
            ans = unsigned_subtr_op(x, y);
            ans.sign = -1;
            return ans;
        }
        if(x.sign == -1 && bigger_sum == 2){
            ans = unsigned_subtr_op(y, x);
            ans.sign = 1;
            return ans;
        }
        if(x.sign == 1 && bigger_sum == 1){
            ans = unsigned_subtr_op(x ,y);
            ans.sign = 1;
            return ans;
        }
        if(x.sign == 1 && bigger_sum == 2){
            ans = unsigned_subtr_op(y ,x);
            ans.sign = -1;
            return ans;
        }
    }
} //знаковое сложение
struct int1024_t subtr_op (struct int1024_t x, struct int1024_t y){
    struct int1024_t ans;
    if (y.sign == -1){
        y.sign = 1;
        return add_op(x, y);
    }
    if( y.sign == 1 && x.sign == -1){
        ans = unsigned_add_op(x, y);
        ans.sign = -1;
        return ans;
    }
    if(y.sign == 1 &&  x.sign == 1){
        if(unsigned_compare_op(x,y) == 1){
            return unsigned_subtr_op(x,y);
        }
        if (unsigned_compare_op(x,y) == 2){
            ans = unsigned_subtr_op(y, x);
            ans.sign = -1;
            return ans;
        }
        if(unsigned_compare_op(x, y) == 0){
            ans = become_zero();
            return ans;
        }
    }
}//знаковое вычитание
struct int1024_t first, second;
void scanf_value (struct int1024_t x){
    x = become_zero();
    char c;
    int i = 0;
    x.sign = 1;
    x.error = 0;

    while(1 == 1)
    {
        scanf("%c", &c);
        if(c == '\n' || c == ' '){
            break;
        }
        if(c == '-'){
            x.sign = -1;
            continue;
        }
        x.num[i] = c;
        i++;
    }
    if (i > 1024){
        x.error = 1;
    }
    int move = 1024 - i;

    for(int j = move, l = 0; j < 1024; ++j, ++l){
        x.num[j] = x.num[l];
        x.num[l] = '0';
    }
    printf_value( x );
}
int main() {
    setlocale(LC_ALL, "Rus");
    printf("%s", "")
}
