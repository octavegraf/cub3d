#include "libft/libft.h"
#include "mlx/mlx.h"
#include <stdio.h>
#include "files.h"

int main(void)
{
	void	*mlx;
	
	mlx = mlx_init();
	if (!mlx)
	{
		ft_putstr_fd("Error: Failed to initialize MLX\n", 2);
		return (1);
	}
	printf("MLX initialized successfully! String length: %zu\n", ft_strlen("TEST"));
	return (0);
}