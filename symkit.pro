TEMPLATE = subdirs

SUBDIRS += \
        symath \
        symgraph \
        symplot \
        symviewer \
        alpha \
        beta

symgraph.depends = symath
symplot.depends = symath symgraph
symviewer.depends = symath symgraph symplot

alpha.depends = symath symgraph
beta.depends = symath symgraph symplot symviewer
