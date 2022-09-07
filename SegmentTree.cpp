/*
    This program was made for academic purposes, feel free to use it.
    By Murilo M. Grosso - 2022
*/

#include <iostream>
#include <algorithm>

void build(int* array, int index, int left, int right);
void update(int pos, int newValue, int index, int left, int right);
int sum(int leftBound, int rightBound, int index, int left, int right);

int* tree;

/*
    <Summary> Calls the tree building function.
    Make sure to set a size and the array elements.
*/
int main()
{
    int size;
    int* array;

    array = new int[size];
    tree = new int[2*size];

    build(array, 1, 0, size - 1);

    delete[] array;
    delete[] tree;

    return 0;
}

/*
    <Summary> Recursively sets the tree nodes. 
    The node vaule represent the sum of its elements.
    It is computed by the sum of its two children vaules, 
    which elements are half the parent ones.
*/
void build(int* array, int index, int left, int right)
{
    if(left == right)
    {
        tree[index] = array[left];
        return;
    }

    int mid = (left + right) / 2;
    build(array, 2*index, left, mid);
    build(array, 2*index + 1, mid + 1, right);
    tree[index] = tree[2*index] + tree[2*index + 1];
}

/*
    <Summary> Change an element and update the nodes vaules recursively.
*/
void update(int pos, int newValue, int index, int left, int right)
{
    if(left == right)
    {
        tree[index] = newValue;
        return;
    }

    int mid = (left + right) / 2;
    if(pos <= mid)
        update(2*index, left, mid, pos, newValue);
    else
        update(2*index + 1, mid + 1, right, pos, newValue);

    tree[index] = tree[2*index] + tree[2*index + 1];
}

/*
    <Summary> Get the sum of a given range.
*/
int sum(int leftBound, int rightBound, int index, int left, int right)
{
    if(leftBound > rightBound)
        return 0;
    if(leftBound == left && rightBound == right)
        return tree[index];

    int mid = (left + right) / 2;
    return sum(2*index, left, mid, leftBound, std:min(rightBound, mid))
        + sum(2*index + 1, mid + 1, right, std::max(leftBound, mid + 1), rightBound);
}
