#ifndef LIB_VARIADIC_H_
#define LIB_VARIADIC_H_

typedef char *      va_list;
#define VA_ROUND(t)      ((sizeof(t) + 1) & ~1u)
#define va_start(ap, l)  ((ap) = (char *)&(l) + VA_ROUND(l))
#define va_arg(ap, t)    (*(t *)(((ap) += VA_ROUND(t)) - VA_ROUND(t)))
#define va_end(ap)       ((void)0)

#endif /* LIB_VARIADIC_H_ */
