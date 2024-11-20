local M = {}

M.example1 = {
    vertices = {
        [1] = { 1.0049010257642959, 0.6312209291156612 },
        [2] = { 1.1739667975447974, 0.016103884286092995 },
        [3] = { 2.152339568447421, 0.3125834733391267 },
        [4] = { 0.4524796482899485, 1.2394622883049342 },
        [5] = { 0., 0.5703941820652277 },
        [6] = { 0.23936219525890257, 0. },
        [7] = { 1.6399249510125273, 1.0893823325872782 }
    },
    edges = {
        [1] = { 2, 3, 4, 5, 6, 7 },
        [2] = { 1, 3, 5, 6, 7 },
        [3] = { 1, 2, 7 },
        [4] = { 1, 5, 6, 7 },
        [5] = { 1, 2, 4, 6 },
        [6] = { 1, 2, 4, 5 },
        [7] = { 1, 2, 3, 4 },
    }
}

local function generate_example2()
    local g = {
        vertices = {},
        edges = {},
    }

    local r1 = 0.8
    local r2 = 0.4

    for i = 1, 7, 1 do
        local x, y = r1 * math.cos(2 * math.pi / 7 * i), r1 * math.sin(2 * math.pi / 7 * i)
        g.vertices[i] = { x, y }
        g.edges[i] = { 1 + (i % 7) }
    end

    for i = 1, 7, 1 do
        local x, y = r2 * math.cos(2 * math.pi / 7 * i), r2 * math.sin(2 * math.pi / 7 * i)
        g.vertices[i+7] = { x, y }
        g.edges[i+7] = { 8 + (i % 7) }
    end

    return g
end

M.example2 = generate_example2()

return M
