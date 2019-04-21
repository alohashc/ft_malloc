/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alohashc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 12:58:45 by alohashc          #+#    #+#             */
/*   Updated: 2019/04/21 12:58:58 by alohashc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_uitoa_base_r(const uintmax_t nmb, const unsigned int base,
							const char base_case, char *mem)
{
	if (nmb < base)
	{
		if (nmb < 10)
			mem[ft_strlen(mem)] = '0' + nmb;
		else
			mem[ft_strlen(mem)] =
				((base_case >= 'a' && base_case <= 'z') ? 'a' : 'A') + nmb - 10;
	}
	else
	{
		ft_uitoa_base_r(nmb / base, base, base_case, mem);
		ft_uitoa_base_r(nmb % base, base, base_case, mem);
	}
}

char		*ft_uitoa_base(const uintmax_t nmb, const unsigned int base,
							const char base_case)
{
	char			*rt;
	unsigned int	dg_am;
	uintmax_t		nmb_cp;

	dg_am = 1;
	nmb_cp = nmb;
	while (nmb_cp != 0 && dg_am++)
		nmb_cp = (nmb_cp < base) ? 0 : nmb_cp / base;
	if ((rt = ft_strnew(dg_am)))
		ft_uitoa_base_r(nmb, base, base_case, rt);
	return (rt);
}

char		*ft_uitoa(const uintmax_t nmb)
{
	return (ft_uitoa_base(nmb, 10, 'a'));
}

char		*ft_itoa_base(const intmax_t nmb, const unsigned int base,
							const char base_case)
{
	char	*rt;
	char	*temp;

	rt = ft_uitoa_base(ABS(nmb), base, base_case);
	if (nmb < 0)
	{
		temp = ft_strjoin("-", rt);
		ft_strdel(&rt);
		rt = temp;
	}
	return (rt);
}
