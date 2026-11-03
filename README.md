# Testeur Libft

Testeur en C pour les **43 fonctions du sujet v19.3**, listes chaînées comprises.
Toutes les fonctions sont obligatoires.

## Utilisation

Place ta bibliothèque dans le dossier `Libft` à côté de `TDDLibft` :

```text
├── Libft/
│   ├── Makefile
│   ├── libft.h
│   └── ft_*.c
└── TDDLibft/
```

Depuis `TDDLibft` :

```sh
make
make run
```

`make` compile la bibliothèque et le testeur. `make run` lance tous les tests
et affiche un bilan. Les sources de ta bibliothèque ne sont pas modifiées.

Si ta Libft est ailleurs, change simplement `LIBFT_DIR` en haut du Makefile,
une fois. Ensuite, utilise toujours `make` et `make run`.

Prérequis : Linux, un compilateur C et `make`. Aucun Python nécessaire.

## Résultats

- `OK` : les cas testés passent.
- `KO` : une vérification échoue, avec le détail attendu / obtenu.
- `CRASH` : la fonction plante ; les autres tests continuent.
- `TIMEOUT` : la fonction dépasse le délai de 3 secondes ; les tests continuent.

Le sujet v19.3 exige notamment des retours `0` ou `1` pour les classifications,
un pointeur non nul et libérable pour `calloc` avec une taille nulle, et le
prototype `unsigned int ft_lstsize(t_list *lst)`. Les prototypes incompatibles
sont signalés à la compilation. Les 43 fonctions doivent être intégrées dans
la cible par défaut de ta Libft ; aucune cible bonus n’est appelée.

`make clean` nettoie les objets du testeur, `make fclean` supprime aussi son
exécutable. Ces commandes ne nettoient pas ta Libft.

Les tests ne remplacent pas la Norm ou une vérification mémoire avec Valgrind.
Les échecs de `malloc` ne sont pas simulés.
