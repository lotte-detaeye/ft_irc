/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:33:31 by lde-taey          #+#    #+#             */
/*   Updated: 2025/08/01 16:39:31 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

Server::Server()
{
	std::cout << "Server Default constructor called" << std::endl;
}

Server::Server(const Server& other)
{
	std::cout << "Server Copy constructor called" << std::endl;
	*this = other;
}

Server& Server::operator=(const Server& other)
{
	std::cout << "Server Copy Assignment constructor called" << std::endl;
	if (this != &other) 
	{
		// copy fields here
	}
	return *this;
}

Server::~Server() 
{
	std::cout << "Server Destructor called" << std::endl;
}