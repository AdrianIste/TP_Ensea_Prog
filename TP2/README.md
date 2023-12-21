Que retenir du TP ?

Le socket sert de passerelle entre le "serveur" et le "client"

En TFTP, on communique en UDP, cela signifie qe l'on a pas besoin de connection au préalable.

Dans les blocs "data" en TFTP, les données sont de maximums 512 octets par blocs, on y ajoute ensuite le header (4 octets) on se retrouve avec des paquets de 516 octets au maximum.
