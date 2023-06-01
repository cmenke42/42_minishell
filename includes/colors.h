/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:18:07 by cmenke            #+#    #+#             */
/*   Updated: 2023/05/29 19:04:42 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

//ESC[style;color_value_type;R;G;Bstop
//\x1B[38;2;255;0;204m"
# define STYLE_DEFAULT "\033[0m"
# define BOLD_PINK "\033[1;38;2;255;0;204m"

#endif