#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/stock.h"

int main() {
    char utilisateur[20];
    char mot_de_pass[10];
    printf("Entrer nom d'utilisateur: ");
    scanf("%s", utilisateur);
    printf("Entrer mot de passe: ");
    scanf("%s", mot_de_pass);

    if (authentifier("authentificateur.txt", utilisateur, mot_de_pass)) {
        printf("Authentification réussie!\n");
    } else {
        printf("Nom d'utilisateur ou mot de passe incorrect.\n");
    }

    return 0;
}

}
