#include "../includes/libftasm.h"
#include <stdio.h>
#include <stdlib.h>
#include <ar.h>
#include <string.h>

// extern void print(void);

int     main(int ac, char **av)
{
    // int fd;
    // // struct ar_hdr header;
    // // char   *str;
    char   *str;

    // ft_reverse_string("test");
    //ft_putnbr(-86515);
    // str = ft_memalloc(15);
    // printf("str %s\n", str);
    // str = strcpy(str, "12345678912345");
    // printf("str %s\n", str);

    // // printf("%d\n", strncmp(str, "123457", 0));
    // // printf("%d\n", ft_strncmp(str, , 0));
    
    str = ft_strndup("hello", 1);
    printf("%s\n", str);
    free(str);

    str = strndup("hello", 1);
    printf("%s\n", str);
    free(str);
    // printf("%d\n", ac);
    // fd = open(av[1], O_RDONLY);
    // ft_cat(fd);
    // close(fd);
    //ft_putstr("testingnfelib fjbfjebjkfebskflsffneislfns\n");
    //printf("%d\n", ft_strlen("efjkwbfueawlifbevwauyifbew;iufv;iuwafveyiawfvi;uwavuifvaulfi\n"));
    //ft_bzero(&header, sizeof(struct ar_hdr));
    //printf("%lu\n", sizeof(struct ar_hdr));
    // str = (char *)malloc(sizeof(char) * 16);
    // str = strcpy(str, "test");
    // // printf("%s\n", str);
    // // ft_bzero(str, 16);
    // // // bzero(str, 16);
    // // printf("%s\n", str);
    // // printf("%d\n", ft_toupper(23));
    // // printf("%d\n", toupper(23));
    // // printf("%s\n", strcat(str, "ing"));
    // free(str);
    // str = (char *)malloc(sizeof(char) * 5);
    // str = strcpy(str, "test");
    // //ft_puts(str);
    // //printf("first %s\n", ft_strcat("test", "in"));
    // // printf("second %s\n", ft_strcat(str, "ing"));
    // //printf("%s\n", (strcat(str, "inggegsges")));
    // free(str);
    // str = (char *)malloc(sizeof(char) * 10);
    // str = strcpy(str, "test");
    // s2 = (char *)malloc(sizeof(char) * 10);
    // s2 = strcpy(s2, "123456789");
    // printf("%s\n", str);
    // printf("%s\n", ft_memcpy(str, s2, strlen(s2)));
    // free(str);
    // str = (char *)malloc(sizeof(char) * 10);
    // str = strcpy(str, "test");
    // printf("%s\n", memcpy(str, s2, strlen(s2)));
    // printf("%s\n", strdup("testing\n"));
    // printf("%s\n", ft_strdup("testing\n"));
    // str = strdup("testing\n");
    // printf("%s\n", str);
    // free(str);
    // s2 = ft_strdup("tesdwdnwakdudgywagdting\n");
    // printf("%d\n", 2);
    // printf("%s\n", s2);
    // free(s2);
    return (0);
}
