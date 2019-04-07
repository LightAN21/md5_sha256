#!/bin/sh

echo "\nTestcase 1:"
echo "echo \"pickle rick\" | ./ft_ssl sha256"
echo "pickle rick" | ./ft_ssl sha256
echo "-------------------------------------------------------"
echo "echo \"pickle rick\" | openssl sha -sha256"
echo "pickle rick" | openssl sha -sha256
echo "=======================================================\n"

echo "\nTestcase 2:"
echo "echo \"Do not pity the dead, Harry.\" | ./ft_ssl sha256 -p"
echo "Do not pity the dead, Harry." | ./ft_ssl sha256 -p
echo "echo \"Do not pity the dead, Harry.\" | openssl sha -sha256"
echo "Do not pity the dead, Harry." | openssl sha -sha256
echo "=======================================================\n"

echo "\nTestcase 3:"
echo "echo \"And abobve all,\" > file"
echo "And abobve all," > file
echo "./ft_ssl sha256 file"
./ft_ssl sha256 file
echo "-------------------------------------------------------"
echo "openssl sha -sha256 file"
openssl sha -sha256 file
echo "=======================================================\n"


echo "\nTestcase 4:"
echo "./ft_ssl sha256 -r file"
./ft_ssl sha256 -r file
echo "=======================================================\n"


echo "\nTestcase 6:"
echo "some of this will not make sense at first" | ./ft_ssl sha256 file
echo "-------------------------------------------------------"
echo "some of this will not make sense at first" | openssl sha -sha256 file
echo "=======================================================\n"


echo "\nTestcase 7:"
echo "echo \"but eventually you will understand\" | ./ft_ssl sha256 -p -r file"
echo "but eventually you will understand" | ./ft_ssl sha256 -p -r file
echo "=======================================================\n"


echo "\nTestcase 8:"
echo "echo \"GL HF let's go\" | ./ft_ssl sha256 -p -s \"foo\" file"
echo "GL HF let's go" | ./ft_ssl sha256 -p -s "foo" file
echo "=======================================================\n"


echo "\nTestcase 9:"
echo "echo \"one more thing\" | ./ft_ssl sha256 -r -p -s \"foo\" file -s \"bar\""
echo "one more thing" | ./ft_ssl sha256 -r -p -s "foo" file -s "bar"
echo "=======================================================\n"


echo "\nTestcase 10:"
echo "echo \"just to be extra clear\" | ./ft_ssl sha256 -r -q -p -s \"foo\" file"
echo "just to be extra clear" | ./ft_ssl sha256 -r -q -p -s "foo" file
echo "=======================================================\n"


echo "\nTestcase 11:"
echo "echo \"just to be extra clear\" | ./ft_ssl sha256 -r -q -p -s"
echo "just to be extra clear" | ./ft_ssl sha256 -r -q -p -s
echo "=======================================================\n"


echo "\nTestcase 12:"
echo "echo \"123\" | ./ft_ssl sha256 -r -p -s file file"
echo "123" | ./ft_ssl sha256 -r -p -s file file
echo "=======================================================\n"


echo "\nTestcase 13:"
echo "echo \"123\" | ./ft_ssl sha256 -s \"abcde\" -r -p -s file file"
echo "123" | ./ft_ssl sha256 -s "abcde" -r -p -s file file
echo "=======================================================\n"
