# Woody_woodpacker
Usage: git clone "repository path" "file name".

Make puis ./woody_woodpacker "file name" sur un fichier binaire de test, cela créer un éxécutable "woody".
# Subject
Woody_woodpacker créer un binaire identique au fichier de test, l'éxécutable "woody" aura donc le même comportement que le fichier de test, à un detail près, il affichera le message "WOODY" au début de son éxécution.

Woody_woodpacker copie un binaire en encryptant les parties éxécutable de ce dernier et en injectant du code dedans. Le code injecter permettra d'afficher le message voulu au début de l'éxécution mais il permettra aussi de décrypter les parties éxécutable à l'éxécution du programme.

L'algorithme d'encryptage est codé en assembleur, les fichiers utilisés seront des fichiers de type ELF64, ELF32, macho64, macho32.
