import profile
import pstats
import pyste

import elementtree.XMLTreeBuilder as XMLTreeBuilder
import GCCXMLParser


if __name__ == '__main__':
    #psyco.bind(XMLTreeBuilder.fixtext)
    #psyco.bind(XMLTreeBuilder.fixname)
    #psyco.bind(XMLTreeBuilder.TreeBuilder)
    #psyco.bind(GCCXMLParser.GCCXMLParser)
    profile.run('pyste.main()', 'profile')
    p = pstats.Stats('profile')
    p.strip_dirs().sort_stats('cumulative').print_stats()
