#include "../include/vecteur.h"
#include "../include/mlxinit.h"

typedef struct s_projectile {
    t_tuple position;
    t_tuple velocity;
} t_projectile;

typedef struct s_environment {
    t_tuple gravity;
    t_tuple wind;
} t_environment;

typedef struct s_simulation {
    t_tuple position;
    t_tuple velocity;
    t_tuple gravity;
    t_tuple wind;
    t_mlx *mlx;
    int is_running;
} t_simulation;

t_projectile tick(t_environment env, t_projectile proj) {
    t_tuple newPosition = add_tuples(proj.position, proj.velocity);
    t_tuple newVelocity = add_tuples(proj.velocity, add_tuples(env.gravity, env.wind));
    return (t_projectile){newPosition, newVelocity};
}


t_mlx *init_graphics(void) {
    t_mlx *mlx = mlx_init_and_create_window(800, 600, "Projectile Simulation");
    if (!mlx || !mlx_create_image(mlx)) {
        mlx_cleanup(mlx);
        exit(1);
    }
    return mlx;
}


#include <stdlib.h>
#include <stdio.h>

// Vos définitions de structures et prototypes de fonctions ici
// t_mlx, t_tuple, t_projectile, t_environment, etc.

void fill_image_with_color(t_mlx *mlx, int color) {
    int x, y;

    for (y = 0; y < mlx->height; y++) {
        for (x = 0; x < mlx->width; x++) {
            int pixel = (y * mlx->line_length) + (x * (mlx->bits_per_pixel / 8));
            *(unsigned int *)(mlx->addr + pixel) = color;
        }
    }
}

// Fonction de mise à jour de la simulation appelée par mlx_loop_hook
int update_simulation(void *param) {
    t_simulation *sim = (t_simulation *)param;
    if (!sim->is_running) return 0; // Stoppe la simulation si is_running est faux

    fill_image_with_color(sim->mlx, 0x007770); // Remplit l'image avec une couleur de fond

    // Mise à jour de la position et de la vitesse du projectile
    sim->velocity = add_tuples(sim->velocity, add_tuples(sim->gravity, sim->wind));
    sim->position = add_tuples(sim->position, sim->velocity);

    // Dessine le projectile à sa nouvelle position
    int x = (int)sim->position.x;
    int y = sim->mlx->height - (int)sim->position.y; // Conversion pour affichage
    draw_square(sim->mlx, x, y, 5, 0x00FF0000); // Dessine en rouge

    // Vérifie la condition de fin
    if (sim->position.y < 0 || x < 0 || x >= sim->mlx->width) {
        sim->is_running = 0; // Marque la simulation comme terminée
        mlx_destroy_image(sim->mlx->ptr, sim->mlx->img); // Nettoie l'image
        // Il n'est pas recommandé d'appeler exit ici; utilisez plutôt un mécanisme pour terminer proprement
    }

    // Affiche l'image mise à jour
    mlx_put_image_to_window(sim->mlx->ptr, sim->mlx->win, sim->mlx->img, 0, 0);

    return 1; // Continue la simulation
}

void simulate_projectile(t_mlx *mlx) {
    t_simulation sim = {
        .position = vector(0, 1, 0), // Position initiale
        .velocity = normalize_tuple(vector(1, 1.8, 0)), // Vitesse initiale
        .gravity = vector(0, -0.1, 0), // Gravité
        .wind = vector(-0.01, 0, 0), // Vent
        .mlx = mlx,
        .is_running = 1, // Commence la simulation
    };

    mlx_loop_hook(mlx->ptr, update_simulation, &sim); // Configure la fonction de mise à jour
}

int main() {
    t_mlx *mlx = mlx_init_and_create_window(800, 600, "Projectile Simulation");
    if (!mlx) return EXIT_FAILURE;

    simulate_projectile(mlx);
    mlx_loop(mlx->ptr); // Démarre la boucle d'événements

    mlx_cleanup(mlx); // Nettoie et libère les ressources de MinilibX
    return EXIT_SUCCESS;
}