local M = {}

local scale = 4

---@alias Point number[]

---@class Graph
---@field vertices table<number, Point>
---@field edges table<number, number[]>

local function contains(tab, val)
    for index, value in ipairs(tab) do
        if value == val then
            return true
        end
    end

    return false
end

---@param G Graph
---@param v number
function M.get_degree(G, v)
    return #G.edges[v]
end

---@param G Graph
function M.deg_matrix(G)
    local size = #G.vertices

    for i = 1, size do
        local row = {}
        for j = 1, size do
            if i == j then
                row[#row+1] = M.get_degree(G, i)
            else
                row[#row+1] = 0
            end
        end

        tex.print(table.concat(row, " & ") .. [[\\]])
    end
end

---@param G Graph
function M.adj_matrix(G)
    local size = #G.vertices

    for i = 1, size do
        local row = {}
        for j = 1, size do
            if contains(G.edges[i], j) then
               row[#row+1] = 1
            else
               row[#row+1] = 0
            end
        end

        tex.print(table.concat(row, " & ") .. [[\\]])
    end
end

---@param G Graph
function M.graph_tikz(G)
    local nodes = {}
    local edges = {}

    for v, coord in pairs(G.vertices) do
        nodes[#nodes + 1] = string.format(
            [[\node[vertex] (%d) at (%f, %f) {$v_%d$};]],
            v,
            coord[1] * scale, coord[2] * scale,
            v
        )
    end

    for ei, adj in pairs(G.edges) do
        for _, ej in pairs(adj) do
            edges[#edges + 1] = string.format(
                [[\draw[edge] (%d) -- (%d);]],
                ei, ej
            )
        end
    end

    tex.print(nodes)
    tex.print(edges)
end

return M
