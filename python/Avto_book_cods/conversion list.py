# на входе spam=['apples', 'bananas', 'tofu', 'cats']
# на выходе 'apples, bananas, tofu, and cats'

'''
# 1й способ
def lists(list_in):
    st=str()
    for el in list_in[:-1]:
        st+=el+', '

    return "'"+st+'and '+list_in[-1]+"'"   

spam=['apples', 'bananas', 'tofu', 'cats']
print(lists(spam))
'''
# 2й способ
def lists(list_in): 
    without_last = list_in[:-1] 
    result = ', '.join(without_last) + ' and ' + list_in[-1] 
    return result 
spam=['apples', 'bananas', 'tofu', 'cats'] 
print(lists(spam))
