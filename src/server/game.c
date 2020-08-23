#include <stdlib.h>
#include <stdio.h>

#include "game.h"

int add_client(game_t *game, client_t *client) {
    client_node_t *previous;
    client_node_t *current = game->root;

    client_node_t *new_node = malloc(sizeof(client_node_t));
    if (!new_node) {
        /* TODO: Error handling */
        puts("Error malloc add client");
        return 0;
    }
    new_node->value = client;
    new_node->color = RED_NODE;

    /* The tree has no root element */
    if (!game->root) {
        game->root = new_node;
        new_node->color = BLACK_NODE;
    } else {
        while (current != NULL) {
            previous = current;
            if (current->value->id < client->id) {
                current = current->left;
            } else if (current->value->id > client->id) {
                current = current->right;
            } else {
                free(new_node);
                return 0;
            }
        }

        new_node->parent = previous;

        if (previous->value->id < client->id) {
            previous->left = new_node;
        } else {
            previous->right = new_node;
        }

    }

    game->nr_clients++;

}

void remove_client(game_t *game, client_t *client) {

}

void fill_outside_tree_array(client_node_t* *array[], client_node_t* c0, client_node_t* c1, client_node_t* c2, client_node_t* c3) {
    *array[0] = c0;
    *array[1] = c1;
    *array[2] = c2;
    *array[3] = c3;
}

void validate_game_tree(game_t *game, client_node_t *client_node) {
    client_node_t *parent = client_node->parent;
    if (!parent) { return; }

    client_node_t *grandparent = parent->parent;
    if (!grandparent) { return; }

    if (parent->color == BLACK_NODE) {
        return;
    } else {
        client_node_t *outside_trees[4];
        int gp_id = grandparent->value->id;
        int p_id = parent->value->id;
        int c_id = client_node->value->id;
        if (gp_id > p_id && p_id > c_id) {
            fill_outside_tree_array((client_node_t ***) &outside_trees, client_node->left, client_node->right, parent->right, grandparent->right);
            parent->parent = grandparent->parent;
            if (parent->parent->left == grandparent) {
                parent->parent->left = parent;
            } else {
                parent->parent->right = parent;
            }
            parent->left = grandparent;
            parent->right = client_node;
            grandparent->parent = parent;
            client_node->parent = parent;
        } else if (gp_id > p_id && p_id < c_id) {
            fill_outside_tree_array((client_node_t ***) &outside_trees, parent->left, client_node->left, client_node->right, grandparent->right);
        } else if (gp_id < p_id && p_id > c_id) {
            fill_outside_tree_array((client_node_t ***) &outside_trees, grandparent->left, client_node->left, client_node->right, parent->right);
        } else {
            fill_outside_tree_array((client_node_t ***) &outside_trees, grandparent->left, parent->left, client_node->left, client_node->right);
        }
    }
}


client_t **get_all_clients(game_t *game);
