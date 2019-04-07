#!/bin/sh

echo "\nTestcase 1:"
echo "echo \"pickle rick\" | ./ft_ssl md5"
echo "pickle rick" | ./ft_ssl md5
echo "-------------------------------------------------------"
echo "echo \"pickle rick\" | md5"
echo "pickle rick" | md5
echo "=======================================================\n"

echo "\nTestcase 2:"
echo "echo \"Do not pity the dead, Harry.\" | ./ft_ssl md5 -p"
echo "Do not pity the dead, Harry." | ./ft_ssl md5 -p
echo "-------------------------------------------------------"
echo "echo \"Do not pity the dead, Harry.\" | md5 -p"
echo "Do not pity the dead, Harry." | md5 -p
echo "=======================================================\n"

echo "\nTestcase 3:"
echo "echo \"And abobve all,\" > file"
echo "And abobve all," > file
echo "./ft_ssl md5 testfile"
./ft_ssl md5 testfile
echo "-------------------------------------------------------"
echo "md5 testfile"
md5 testfile
echo "=======================================================\n"


echo "\nTestcase 4:"
echo "./ft_ssl md5 -r file"
./ft_ssl md5 -r file
echo "-------------------------------------------------------"
echo "md5 -r file"
md5 -r file
echo "=======================================================\n"


echo "\nTestcase 5:"
echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p file
echo "-------------------------------------------------------"
echo "be sure to handle edge cases carefully" | md5 -p file
echo "=======================================================\n"


echo "\nTestcase 6:"
echo "some of this will not make sense at first" | ./ft_ssl md5 file
echo "-------------------------------------------------------"
echo "some of this will not make sense at first" | md5 file
echo "=======================================================\n"


echo "\nTestcase 7:"
echo "but eventually you will understand" | ./ft_ssl md5 -p -r file
echo "-------------------------------------------------------"
echo "but eventually you will understand" | md5 -p -r file
echo "=======================================================\n"


echo "\nTestcase 8:"
echo "GL HF let's go" | ./ft_ssl md5 -p -s "foo" file
echo "-------------------------------------------------------"
echo "GL HF let's go" | md5 -p -s "foo" file
echo "=======================================================\n"


echo "\nTestcase 9:"
echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" file -s "bar"
echo "-------------------------------------------------------"
echo "one more thing" | md5 -r -p -s "foo" file -s "bar"
echo "=======================================================\n"


echo "\nTestcase 10:"
echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" file
echo "-------------------------------------------------------"
echo "just to be extra clear" | md5 -r -q -p -s "foo" file
echo "=======================================================\n"


echo "\nTestcase 11:"
echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s
echo "-------------------------------------------------------"
echo "just to be extra clear" | md5 -r -q -p -s
echo "=======================================================\n"


echo "\nTestcase 12:"
echo "123" | ./ft_ssl md5 -r -p -s file file
echo "-------------------------------------------------------"
echo "123" | md5 -r -p -s file file
echo "=======================================================\n"


echo "\nTestcase 13:"
echo "123" | ./ft_ssl md5 -s "abcde" -r -p -s file file
echo "-------------------------------------------------------"
echo "123" | md5 -s "abcde" -r -p -s file file
echo "=======================================================\n"



