#!/bin/python3

from urllib.request import urlopen
import json
import os

cur_dir = os.getcwd()

with open(cur_dir + "/submissions.json") as f:
    submissions = json.load(f)

with urlopen("https://uhunt.onlinejudge.org/api/p") as response:
    names = json.load(response)

ac_submissions = []

for sub in submissions['subs']:
    if sub[2] == 90:
        ac_submissions.append([sub[1], sub[6], sub[0], sub[5]])

ac_submissions.sort()
unique_ac = []
ids = []

for ac in ac_submissions:
    if len(unique_ac) > 0 and unique_ac[-1][1] == ac[0]:
        pass
    else:
        unique_ac.append([ac[2], ac[0], ac[1], ac[3]])
        ids.append(ac[0])

unique_ac.sort(reverse=True)

number_name = {}
tobe_created = open("./solutions/number_name.txt", "w")

for name in names:
    if name[0] in ids:
        number_name.update({'{}'.format(name[0]):[name[1], name[2]]})
        tobe_created.write(str(name[1]) + ' - ' + str(name[2]) + '.cpp,')

tobe_created.close()

root_url = "https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&"
prob_url = root_url + 'problem' + '=' + '{problem_id}'

langs = {"1":"ANSI C", "2":"Java", "3":"C++", "4":"Pascal", "5":"C++11"}

print('|  #  | Submission ID | Problem Name | Submission Rank | Language |')
print('| :-: | :-----------: | :----------: | :-------------: | :------: |')
counter = len(unique_ac)

for ac in unique_ac:
    print('| ', counter, ' |', sep='', end='')
    print(' [', ac[0], '](./uva-oj/solutions/', number_name['{}'.format(ac[1])][0], ' - ', number_name['{}'.format(ac[1])][1] , '.cpp)', sep='', end=' |')
    print(' [', number_name['{}'.format(ac[1])][0], ' - ', number_name['{}'.format(ac[1])][1], '](', prob_url.format(problem_id=ac[1]), ')', sep='', end=' |')
    print(' ', ac[2], sep='', end=' |')
    print(' ', langs['{}'.format(ac[3])], sep='', end=' |')
    print('')
    counter -= 1
