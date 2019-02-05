#!/usr/bin/env Rscript
args = commandArgs(trailingOnly=TRUE)

Numeros = as.numeric(args[2:length(args)])

Nombre = as.character(args[1])

Numeros_frame = data.frame(Numeros)

mediana = median(Numeros)

media = mean(Numeros)

desvest = sd(Numeros)

#plot = ggplot2::ggplot(Numeros_frame, ggplot2::aes(x = "", y = Numeros)) + ggplot2::geom_boxplot() + ggplot2::ylab("Valores de distancia") + ggplot2::xlab(Nombre)

#dir.create(file.path(getwd(), "Boxplots"), showWarnings = FALSE)

#ggplot2::ggsave(paste0("Boxplots/", Nombre, "_boxplot_.png"), plot = plot, dpi=300)

cat(mediana)

cat("\n")

cat(media)

cat("\n")

cat(desvest)




