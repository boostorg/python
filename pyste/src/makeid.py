
def makeid(name):
    'Returns the name as a valid identifier'
    for invalidchar in ('::', '<', '>', ' ', ','):
        name = name.replace(invalidchar, '_') 
    # avoid duplications of '_' chars
    names = [x for x in name.split('_') if x]
    return '_'.join(names)

