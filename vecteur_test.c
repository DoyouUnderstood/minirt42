/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecteur_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:48:04 by alletond          #+#    #+#             */
/*   Updated: 2024/02/12 18:52:11 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void throw_ray(t_scene scene)
{
    int height = 860;
    int width = 600;
    int x = 0;
    int y = 0;
    while (y <= height)
    {
        x = 0;
        while (x <= width)
        {
            // lancer un rayon pour [x ; y];
            // si ca touche un object faire qla chose.
            // fonction qui determine si ca touche.
            // fonction qui fait qlq chose.
            x++;
        }
        y++;
    }
}
int main()
{
    return (0);
}


