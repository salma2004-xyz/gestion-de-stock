#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Headers/stock.h"

int authentifier(const char* fichier_auth, const char* nom_utilisateur, const char* mot_de_passe) {
    FILE *fichier = fopen(fichier_auth, "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return 0;
    }

    char utilisateur[50], mot_de_pass[50];
    while (fscanf(fichier, "%s %s", utilisateur, mot_de_pass) != EOF) {
        if (strcmp(nom_utilisateur, utilisateur) == 0 && strcmp(mot_de_passe, mot_de_pass) == 0) {
            fclose(fichier);
            return 1;
        }
    }

    fclose(fichier);
    return 0; // User not found or incorrect password
}

void ajouterProduit(const char* fichier, produit p) {
    FILE *f = fopen(fichier, "a");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    fprintf(f, "%s,%s,%s,%.2f,%d,%d-%d-%d,%d-%d-%d,%.2f\n", p.nom, p.description, p.nom_u, p.prix, p.quantite,
            p.date.jour, p.date.mois, p.date.annee, p.date2.jour2, p.date2.mois2, p.date2.annee2, p.seuil);

    fclose(f);
}

void afficherListeProduits(const char* fichier) {
    FILE *f = fopen(fichier, "r");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    produit p;
    while (fscanf(f, "%s %s %s %f %d %d-%d-%d %d-%d-%d %f\n", p.nom, p.description, p.nom_u, &p.prix, &p.quantite,
                  &p.date.jour, &p.date.mois, &p.date.annee, &p.date2.jour2, &p.date2.mois2, &p.date2.annee2, &p.seuil) != EOF) {
        printf("Nom: %s, Description: %s, Prix: %.2f, Quantité: %d, Seuil: %.2f\n", p.nom, p.description, p.prix, p.quantite, p.seuil);
    }

    fclose(f);
}

void supprimerProduit(const char fichier[], const char nomProduit[]) {
    FILE *f = fopen(fichier, "r");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    FILE *temp = fopen("temp.csv", "w");                         // Cree file temporaire pour stocker le produit

    if (temp == NULL) {
        printf("Erreur de création du fichier temporaire.\n");
        fclose(f);
        return;
    }

    produit p;
    int found = 0;
    while (fscanf(f, "%s %s %s %f %d %d-%d-%d %d-%d-%d %f\n", p.nom, p.description, p.nom_u, &p.prix, &p.quantite,
                  &p.date.jour, &p.date.mois, &p.date.annee, &p.date2.jour2, &p.date2.mois2, &p.date2.annee2, &p.seuil) != EOF) {
        // Skip the product to delete
        if (strcmp(p.nom, nomProduit) != 0) {
            fprintf(temp, "%s,%s,%s,%.2f,%d,%d-%d-%d,%d-%d-%d,%.2f\n", p.nom, p.description, p.nom_u, p.prix, p.quantite,
                    p.date.jour, p.date.mois, p.date.annee, p.date2.jour2, p.date2.mois2, p.date2.annee2, p.seuil);
        } else {
            found = 1;
        }
    }

    fclose(f);
    fclose(temp);

    if (found) {
        remove(fichier);
        rename("temp.csv", fichier);
        printf("Produit supprimé.\n");
    } else {
        printf("Produit non trouvé.\n");
        remove("temp.csv");
    }
}
