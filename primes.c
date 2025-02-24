/*
FUNCTIONS:

isSubarray(A[], n, B[], m):
    if length of B > length of A:
        return false
    
    for i from 0 to (length of A - length of B):
        match = true
        for j from 0 to length of B - 1:
            if A[i+j] != B[j]:
                match = false
                break
        if match is true:
            return true
    return false

findIntersection(A[], n, B[], m, resultSize):
    create intersection array of size min(n,m)
    resultSize = 0
    
    for each element a in A:
        for each element b in B:
            if a equals b:
                if a is not already in intersection:
                    add a to intersection
                    increment resultSize
                break
    return intersection array

findUnion(A[], n, B[], m, resultSize):
    create union array of size (n+m)
    resultSize = 0
    
    // Add all elements from A
    for each element a in A:
        if a is not already in union:
            add a to union
            increment resultSize
            
    // Add elements from B
    for each element b in B:
        if b is not already in union:
            add b to union
            increment resultSize
    
    return union array

MAIN:
    Initialize arrays A and B
    Calculate sizes n and m
    
    Check if B is subarray of A using isSubarray()
    Print result
    
    Find intersection using findIntersection()
    Print intersection elements
    
    Find union using findUnion()
    Print union elements
    
    Free dynamically allocated memory
*/
