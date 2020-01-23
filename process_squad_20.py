import io
import json
import numpy as np
import spacy


nlp = spacy.load("en_core_web_md")

f = open("Downloads/dev-v2.0.json", "r")

js = json.load(f)

# maxlen = 0

for jsd in js["data"][0]["paragraphs"]:
    # l =len(jsd["context"])
    # if l > maxlen:
        # maxlen = l
    para = nlp(jsd["context"])

    print("Context: %s" %(para))
    
    for jsd2 in jsd["qas"]:
        qu = nlp(jsd2["question"])
        print("Q: %s" %(qu))

# print("Maxlen (paragraph): %d"%(maxlen))

# maxlen = 0

# for jsd in js["data"][0]["paragraphs"]:
#   for jsd2 in jsd["qas"]:
#       l =len(jsd2["question"])
#       if l > maxlen:
#           maxlen = l

# print("Maxlen (qas): %d"%(maxlen))