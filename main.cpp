/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:30:19 by lde-taey          #+#    #+#             */
/*   Updated: 2025/07/28 15:30:20 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main (int argc, char** argv) 
{
    if (argc != 3) 
    {
        std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
        return (1);
    }
    void(argv); 
    return (0);
}
