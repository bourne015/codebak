
def findItinerary(self, tickets):
    d = {}
    for flight in tickets:
        if not d[flight[0]]:
            d[flight[0]] = [flight[1]]
        else:
            d[flight[0]] += [flight[1]],
    route = ["JFK"]
    dfs(d, tickets, route, "JFK")
    return route

def dfs(d, tickets, route, start):
    if len(route) == len(tickets) + 1:
        return route
    myDsts = sorted(d[start])
    for dst in myDsts:
        d[start].remove(dst)
        route.append(dst)
        worked = dfs(dst)
        if worked:
            return worked
        route.pop()
        d[start] += dst,
if __name__ == "__main__":
    e = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"]
    print(e)
    res = findItinerary(5, e)
    print(res)
