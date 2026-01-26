#ifndef UTILS_H
#define UTILS_H

#define ARRAY_COUNT(arr)  sizeof(arr) / sizeof(arr[0])

#define BIT_SET_BOOL(var, boolVar, mask)  (var) = (((var) & ~(mask)) | ((boolVar) ? (mask) : 0))

#endif
