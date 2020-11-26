from PIL import Image

def gen_full(a):
    with open("tmpfile", "w") as f:
        dfs(a, f, "")

def dfs(a, res, tmp):
    res.write(tmp+'\n')
    for i in range(len(a)):
        dfs(a[:i]+a[i+1:], res, tmp+(a[i]))

if __name__ == "__main__":
    bak_pw = ['(',  'F', ')',  '<', 'T', 't', '>', "?", ',', '.']
    gen_full(bak_pw)
