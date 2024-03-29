# intro-prog-lzw

Introduction to Programming Course LZW Tree

## Summary

This project contains source files and sample data files for lzw tree.
The goal was only to excercise basic cpp, therefore its performance is **BAD**.

## Build
Makefile will write the executable (and objs, defs)  to `./build`.

## Run
Examples:

`cmd ./sample/tiny_bit.txt -o ./temp/tiny_bit.out -b`

In the above command `-b` is used to interpret char '1' as a true bit and '0' as a false bit.

`cmd ./sample/tiny_bit.txt -o ./temp/tiny_bit.out -b -t postorder`

In the above command `-t` is used to with value `postorder`, so this will print results in a **postorder**.

`cmd ./sample/medium_nonbit.txt -o ./temp/medium_nonbit.out`

In the above command `-b` is NOT used therefore the different characters will be treated as 8 separate bits.


If you make a mistake an error will be thrown and the usage will be printed out.

Dont use `-b` for `medium_nonbit.txt` because we want those characters to be treated as 8 separate bits.

If you dont provide any cl args, then the app will print to cout the usage.

## Test

Sample folder provides two example source files and an example output:

1. **tiny_bit.txt** - (Input) This is a small example based on nbatfai's blog. [Labormeres Otthon](https://progpater.blog.hu/2011/03/05/labormeres_otthon_avagy_hogyan_dolgozok_fel_egy_pedat) 
2. **tiny_bit_out.txt** - (Output) The nbatfai's tree inorder rhs-to-lhs printed. [Labormeres Otthon](https://progpater.blog.hu/2011/03/05/labormeres_otthon_avagy_hogyan_dolgozok_fel_egy_pedat) 
3. **medium_nonbit.txt** - (Input) Gene sample from a flying unicorn

Huzzah!